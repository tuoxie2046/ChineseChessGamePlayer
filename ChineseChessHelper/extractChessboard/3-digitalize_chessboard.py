#!/usr/bin/python

import os
import Image, numpy

classes = []
rsize = (48, 48)
cbox = (18, 18, 30, 30)
filepath_m = 'baselibrary/m/m.jpg' 
filepath_M = 'baselibrary/M/M.jpg' 
filepath_c = 'baselibrary/c/c.jpg'
filepath_C = 'baselibrary/C/C.jpg' 
 
def pure(h):
	H = []
	s = 0
	for i, p in enumerate(h):
		if (i+1)%32 == 0:
			H.append(s)
			s = 0
		else:
			s += p
	return H / (numpy.sum(H) + 0.0)


def pureimg(filepath):
	img = Image.open(filepath).crop(cbox).split()[0].histogram()
	return pure(img)

def getCType(filepath):
	ht = pureimg(filepath)
	hc = pureimg(filepath_c)
	hC = pureimg(filepath_C)
	if sum(abs(ht - hc)) < sum(abs(ht - hC)):
		return 'c'
	return 'C'

def getMType(filepath):
	ht = pureimg(filepath)
	hm = pureimg(filepath_m)
	hM = pureimg(filepath_M)
	if sum(abs(ht - hm)) < sum(abs(ht - hM)):
		return 'm'
	return 'M'

def getSimilarity(im1, im2):
	return numpy.mean(abs(im1 - im2))

def getSimilarityAmongClass(im, classfiles):
	sim = 0.0
	for f in classfiles:
		sim += getSimilarity(im, f)
	return sim / len(classfiles)

def getClass(imname):
	global classes
	im = numpy.array(Image.open(imname).resize(rsize), dtype=numpy.float32)
	bestClass, bestSim = None, 1e10
	for c, classfiles in classes:
		sim = getSimilarityAmongClass(im, classfiles)
		if sim < bestSim:
			bestSim = sim
			bestClass = c
	if bestClass == 'c' or bestClass == 'C':
		bestClass = getCType(imname)
	elif bestClass == 'm' or bestClass == 'M':
		bestClass = getMType(imname)
	return bestClass

def readClasses():
	global classes
	classes = []
	cs = os.listdir('baselibrary/')
	for c in cs:
		imgs = []
		files = os.listdir('baselibrary/%s' % c)
		for f in files:
			im = Image.open('baselibrary/%s/%s' % (c, f))
			im = numpy.array(im.resize(rsize), dtype=numpy.float32)
			imgs.append(im)
		classes.append((c, imgs))


readClasses()
player_type = 'r'
s = ''
n = 0
grids = os.listdir('./tmp/grids/')
topgrids = sorted([l for l in grids if l.startswith("top")])
for g in topgrids:
	x, y = g[:-4].split('_')[1:3]
	x, y = int(x), int(y)
	c = getClass('./tmp/grids/%s' % g)
	n += 1
	s += c + ' '
	if n % 9 == 0:
		s += '\n'

botgrids = sorted([l for l in grids if l.startswith("bot")])
for g in botgrids:
	x, y = g[:-4].split('_')[1:3]
	x, y = int(x) + 5, int(y)
	c = getClass('./tmp/grids/%s' % g)
	n += 1
	s += c + ' '
	if n % 9 == 0:
		s += '\n'
	if 7 <= x <= 9 and 3 <= y <= 6:
		if c == 'J':
			player_type = 'b'


f = open('tmp/chessboard.txt', 'w')
f.write(player_type + '\n')
f.write(s + '\n')
f.close()

