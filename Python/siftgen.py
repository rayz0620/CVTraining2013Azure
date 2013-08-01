import sift
import yaml
import cv2

class siftGenerator:
	def __init__(self):
		pass

	def __init__(self, cfgFile):
		loadConfig(cfgFile)

	def loadConfig(self, filename):
		with open(filename) as file:
			config = yaml.load(file)
			self.gridSpacing = config['gridSpacing']
			self.patchSize = config['gridSpacing']
			self.maxImSize = config['maxImSize']
			self.nrml_threshold = config['nrml_threshold']

	def generateSift(self, imgOrFilename):
		if isinstance(imgOrFilename, str):
			image = cv2.imread(imgOrFilename)
			grayImg = grayImg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		else:
			grayImg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		return sift.calculateSiftDescriptor(img, self.gridSpacing, self.patchSize, self.maxImSize, self.nrml_threshold)