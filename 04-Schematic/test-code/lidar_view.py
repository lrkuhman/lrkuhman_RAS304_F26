"""
Live 2D point cloud for the Waveshare D500 / LDRobot LD19-family LiDAR.
OpenField (Team 1) - Landon Kuhman

Data source (either one, both run at 230400 baud):
  - The Curiosity Nano running main.c with TEST_STAGE 6 (LiDAR TX -> RC7):
    use the Nano's "Curiosity Virtual COM Port".
  - The LiDAR's own USB adapter board: use the adapter's COM port.

    pip install pyserial matplotlib numpy
    python lidar_view.py COM5            (use your COM port)

Find the COM port in Windows Device Manager -> Ports (COM & LPT).
Close any serial terminal (Tera Term, PuTTY, MPLAB Data Visualizer) on that
port first.
Close the window or press Ctrl+C to stop.
"""
import sys
import threading

import numpy as np
import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

BAUD = 230400
PKT_LEN = 47
MAX_RANGE_MM = 4000          # plot radius; change to zoom in/out
MIN_INTENSITY = 0            # raise (e.g. 100) to hide weak/noisy returns

# CRC-8, polynomial 0x4D, init 0 (LDRobot protocol)
CRC_TABLE = []
for i in range(256):
    c = i
    for _ in range(8):
        c = ((c << 1) ^ 0x4D) & 0xFF if c & 0x80 else (c << 1) & 0xFF
    CRC_TABLE.append(c)


def crc8(data):
    c = 0
    for b in data:
        c = CRC_TABLE[c ^ b]
    return c


def parse_packet(p):
    """Return (speed_dps, [(angle_deg, dist_mm, intensity), ...]) or None."""
    if len(p) != PKT_LEN or p[0] != 0x54 or p[1] != 0x2C or crc8(p[:46]) != p[46]:
        return None
    speed = p[2] | (p[3] << 8)
    start = (p[4] | (p[5] << 8)) / 100.0
    end = (p[42] | (p[43] << 8)) / 100.0
    if end < start:
        end += 360.0
    step = (end - start) / 11.0
    pts = []
    for i in range(12):
        o = 6 + 3 * i
        dist = p[o] | (p[o + 1] << 8)
        inten = p[o + 2]
        pts.append(((start + step * i) % 360.0, dist, inten))
    return speed, pts


class Reader(threading.Thread):
    """Reads the serial port in the background and keeps the latest full scan."""

    def __init__(self, port):
        super().__init__(daemon=True)
        self.ser = serial.Serial(port, BAUD, timeout=0.1)
        self.lock = threading.Lock()
        self.scan = []          # last complete 360-degree scan
        self.current = []
        self.last_angle = 0.0
        self.speed = 0
        self.good = 0
        self.bad = 0

    def run(self):
        buf = bytearray()
        while True:
            buf += self.ser.read(512)
            while True:
                i = buf.find(b"\x54\x2c")
                if i < 0:
                    del buf[:-1]
                    break
                if len(buf) - i < PKT_LEN:
                    del buf[:i]
                    break
                pkt = bytes(buf[i:i + PKT_LEN])
                res = parse_packet(pkt)
                if res is None:
                    self.bad += 1
                    del buf[:i + 1]       # false header, keep searching
                    continue
                del buf[:i + PKT_LEN]
                self.good += 1
                speed, pts = res
                for ang, dist, inten in pts:
                    if ang < self.last_angle - 180:      # wrapped past 0 deg: scan done
                        with self.lock:
                            self.scan = self.current
                            self.speed = speed
                        self.current = []
                    self.last_angle = ang
                    if dist > 0 and inten >= MIN_INTENSITY:
                        self.current.append((ang, dist, inten))


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    rd = Reader(sys.argv[1])
    rd.start()

    fig = plt.figure(figsize=(7, 7))
    ax = fig.add_subplot(projection="polar")
    ax.set_theta_zero_location("N")       # 0 deg at the top
    ax.set_theta_direction(-1)            # clockwise, like the LiDAR
    ax.set_rlim(0, MAX_RANGE_MM)
    sc = ax.scatter([], [], s=4, c=[], cmap="viridis", vmin=0, vmax=255)
    title = ax.set_title("waiting for data...")

    def update(_):
        with rd.lock:
            scan = list(rd.scan)
            speed = rd.speed
        if scan:
            a = np.radians([p[0] for p in scan])
            d = np.array([p[1] for p in scan])
            sc.set_offsets(np.column_stack([a, d]))
            sc.set_array(np.array([p[2] for p in scan]))
        title.set_text(f"D500 point cloud  |  {speed / 360:.1f} Hz  |  {len(scan)} points  |  "
                       f"good {rd.good}, CRC errors {rd.bad}")
        return sc, title

    _anim = FuncAnimation(fig, update, interval=100, cache_frame_data=False)
    plt.show()


if __name__ == "__main__":
    main()
