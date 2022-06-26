from os.path import splitext

from PyQt5.QtCore import QBuffer, QIODevice, QByteArray
from PyQt5.QtGui import QImage, QIcon
from PyQt5.QtWidgets import QApplication

path = "res/icon.svg"

app = QApplication([])
src = QIcon(path)
files = dict()
sizes = (8, 16, 24, 32, 40, 48, 60, 64, 72, 92, 108, 128, 256)

for size in sizes:
    ba = QByteArray()
    buff = QBuffer(ba)
    buff.open(QIODevice.WriteOnly)
    src.pixmap(size, size).save(buff, "ico")
    buff.close()
    files[size] = bytes(ba)

compressed = bytes([0, 0, 1, 0, len(sizes) % 256, len(sizes) // 256])

offset = 6 + 16 * len(sizes)
for size in sizes:
    compressed += bytes([size % 256, size % 256]) + files[size][8:18] + bytes([offset % 256, offset // 256 % 256, offset // (256 ** 2) % 256, offset // (256 ** 3) % 256])
    offset += files[size][14] + files[size][15] * 256 + files[size][16] * (256 ** 2) + files[size][17] * (256 ** 3)

for size in sizes:
    compressed += files[size][22:]


with open(splitext(path)[0] + ".ico", "wb") as fout:
    fout.write(compressed)