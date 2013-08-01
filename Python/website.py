from siftgen import siftGenerator
from llcoder import LLCoder
import scc_config as config
import cv2

def query(filename):
	#Prepare for calculation
	queryImg = cv2.imread(filename)
	sg = siftGenerator(config.featCfg)
	llc = LLCoder()
	llc.loadConfig(config.llcConfig)
	llc.B = config.llcBase
	llc.pyramid = config.llcPyramid

	feat = sg.calculateSiftDescriptor(queryImg)
	codedFeat = llc.encode(feat)
	startJob(Feat)

def startJob():
	pass
