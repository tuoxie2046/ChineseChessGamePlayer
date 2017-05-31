import os, time

imgfile = "/tmp/cap.jpg"
resfile = "/tmp/res.txt"

def grab():
	if os.path.isfile(resfile):
		os.remove(resfile)
	os.system("screencapture "+imgfile)
	while not os.path.isfile(resfile):
		time.sleep(0.2)
	while os.path.getsize(resfile) == 0:
		time.sleep(0.2)
	print open(resfile).read().decode('utf-8').encode('gb2312')

