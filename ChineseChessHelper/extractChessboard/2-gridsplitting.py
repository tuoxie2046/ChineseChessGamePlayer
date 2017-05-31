#!/usr/bin/python

import numpy
import Image
import pylab
import os

def getleftborder(s):
	bigline = False
	for i, p in enumerate(s):
		if p > 0.4:
			bigline = True
		else:
			if bigline: break
	for i in range(i + 1, len(s)):
		if s[i] > 0.4:
			break
	for j in range(i + 1, len(s)):
		if s[j] < 0.4:
			break
	return (i + j - 1) / 2


def getrightborder(s):
	bigline = False
	for i in range(len(s)-1, 0, -1):
		if s[i] > 0.4:
			bigline = True
		else:
			if bigline: break
	for i in range(i - 1, 0, -1):
		if s[i] > 0.4:
			break
	for j in range(i - 1, 0, -1):
		if s[j] < 0.4:
			break
	return (i + j + 1) / 2


def gettopborder(s):
	bigline = False
	for i, p in enumerate(s):
		if p > 0.05:
			bigline = True
		else:
			if bigline: break
	for i in range(i + 1, len(s)):
		if s[i] > 0.05:
			break
	for j in range(i + 1, len(s)):
		if s[j] < 0.05:
			break
	return (i + j - 1) / 2


def getbottomborder(s):
	bigline = False
	for i in range(len(s)-1, 0, -1):
		if s[i] > 0.05:
			bigline = True
		else:
			if bigline: break
	for i in range(i - 1, 0, -1):
		if s[i] > 0.05:
			break
	for j in range(i - 1, 0, -1):
		if s[j] < 0.05:
			break
	return (i + j + 1) / 2


def getmidtop(s):
	for i in range(len(s)/2, 0, -1):
		if s[i] > 0.4:
			break
	for j in range(i-1, 0, -1):
		if s[j] < 0.4:
			break
	return (i + j + 1) / 2


def getmidbot(s):
	for i in range(len(s)/2, len(s)):
		if s[i] > 0.4:
			break
	for j in range(i + 1, len(s)):
		if s[j] < 0.4:
			break
	return (i + j - 1) / 2


im = Image.open('tmp/chessboard.jpg')
gray = im.convert('L')
mask = gray.point(lambda x: x < 20 and 255)
scol = numpy.sum(mask, axis=0, dtype=numpy.float32)
scol = scol / max(scol)
l, r = getleftborder(scol), getrightborder(scol)
srow = numpy.sum(mask, axis=1, dtype=numpy.float32)
srow = srow / max(srow)
u, d = gettopborder(srow), getbottomborder(srow)
mt, mb = getmidtop(srow), getmidbot(srow)
gridsize = (int(numpy.round((r-l+1)/8.)), int(numpy.round((d-mb+1)/4.)))


os.system('mkdir -p tmp/grids')
# split top grids
for c in range(9):
	for r in range(5):
		pos = (c * gridsize[0] + l, r * gridsize[1] + u)
		pl = pos[0] - gridsize[0] / 2
		pr = pos[0] + gridsize[0] / 2
		pu = pos[1] - gridsize[1] / 2
		pd = pos[1] + gridsize[1] / 2
		im.crop((pl, pu, pr, pd)).save('tmp/grids/top_%d_%d.jpg' % (r, c))


# split bot grids
for c in range(9):
	for r in range(5):
		pos = (c * gridsize[0] + l, r * gridsize[1] + mb)
		pl = pos[0] - gridsize[0] / 2
		pr = pos[0] + gridsize[0] / 2
		pu = pos[1] - gridsize[1] / 2
		pd = pos[1] + gridsize[1] / 2
		im.crop((pl, pu, pr, pd)).save('tmp/grids/bot_%d_%d.jpg' % (r, c))
