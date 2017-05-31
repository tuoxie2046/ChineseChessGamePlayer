#!/usr/bin/python

import os, time

imgfile = "/tmp/cap.jpg"
imgfile_ = "/tmp/_cap.jpg"
resfile = "/tmp/res.txt"

i = 1
gamename = time.strftime('PreviousGames/%Y%m%d%H%M')
os.system('rm -rf %s' % gamename)
os.system('mkdir -p %s' % gamename)

def process():
	global i
	while not os.path.isfile(imgfile):
		time.sleep(0.2)
	print '[%s] start processing...' % time.strftime('%H:%M:%S')
	os.rename(imgfile, imgfile_)
	os.system('./1-extractChessboard.py %s' % imgfile_)
	os.system('./2-gridsplitting.py')
	os.system('./3-digitalize_chessboard.py')
	os.system('./4-alphabetasearch > %s' % resfile)
	print open(resfile).read()
	os.system('cp tmp/chessboard.jpg %s/%d.jpg' % (gamename, i))
	i = i + 1
	print '[%s] end processing...\n' % time.strftime('%H:%M:%S')


while True:
	process()


