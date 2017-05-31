#!/usr/bin/python

import sys, os
import Image, numpy

if len(sys.argv) != 2:
	print 'usage: pic'
	exit()

os.system('mkdir -p tmp')
im = Image.open(sys.argv[1])

th = (180, 210)
mask = im.convert("L")
mask = mask.point(lambda i: th[0] < i < th[1] and 255)

l = 0
scol = numpy.sum(mask, axis=0, dtype=numpy.float32)
scol = scol / max(scol)
for i in xrange(0, len(scol) - 8):
	if scol[i]>0.4 and scol[i+1]>0.4 and scol[i+2]>0.4 and scol[i+3]>0.4 and scol[i+4]>0.4 and scol[i+5]>0.4:
		l = i
		break

r = l
for i in xrange(l, len(scol) - 8):
	if scol[i]<0.3 and scol[i+1]<0.3 and scol[i+2]<0.3 and scol[i+3]<0.3 and scol[i+4]<0.3 and scol[i+5]<0.3:
		r = i
		break

mask = mask.crop((l, 0, r, mask.size[1] - 1))
srow = numpy.sum(mask, axis=1, dtype=numpy.float32)
srow = srow / max(srow)

u = 0
flag = False
for i in xrange(len(srow) - 1):
	if srow[i] > 0.1:
		flag = True
	else:
		if flag: break;

for i in xrange(i + 1, len(srow) - 4):
	if srow[i] > 0.1 and srow[i + 1] > 0.1 and srow[i + 2] > 0.1:
		u = i
		break

d = 0
for i in xrange(u + 1, len(srow) - 10):
	if srow[i]<0.1 and srow[i+1]<0.1 and srow[i+2]<0.1 and srow[i+3]<0.1 and srow[i+4]<0.1 and srow[i+5]<0.1:
		d = i
		break

print l, u, r, d
im2 = im.crop((l, u, r - 1, d - 1))
im2.save('tmp/chessboard.jpg')
