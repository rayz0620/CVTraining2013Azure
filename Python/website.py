from siftgen import siftGenerator
from llcoder import LLCoder
import scc_config as config
import retrieval
import cv2

sg = siftGenerator(config.featCfg)

llc = LLCoder()
llc.loadConfig(config.llcCfg)
llc.B = config.llcBase
llc.pyramid = config.llcPyramid

r = retrieval.Retrieval()
r.loadConfig(config.scCfg)
r.loadMainDB(config.mainDB)
r.loadSemanticDB(config.semDB)

def query(filename):
#Prepare for calculation
	feat = sg.generateSift(filename)
	codedFeat = llc.encode(feat)

	topMatch = r.processQuery(codedFeat, 10)
	print topMatch
	return topMatch

def startJob():
	print 'Hadoop job started'