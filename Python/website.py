from siftgen import siftGenerator
from llcoder import LLCoder
import scc_config as config
import cv2

def query(filename):
	#Prepare for calculation
	#queryImg = cv2.imread(filename)
	sg = siftGenerator(config.featCfg)
	llc = LLCoder()
	llc.loadConfig(config.llcCfg)
	llc.B = config.llcBase
	llc.pyramid = config.llcPyramid
	img = cv2.imread(filename, cv2.CV_LOAD_IMAGE_GRAYSCALE)
	feat = sg.generateSift(filename)
	print feat['feaArr'].shape
	codedFeat = llc.encode(feat)
	startJob()

def startJob():
	print 'Hadoop job started'
