import LLC
import cvyaml
from matrixio import io

class LLCoder:
	def __init__(self):
		self.B = []
		self.pyramid = []
		self.knn = 0

	def loadConfig(self, filename):
		with open(filename) as fs:
			matIO = io()
			cfg = cvyaml.load(fs)
			self.knn = cfg['knn']

	def encode(self, src):
		return LLC.LLC().calculateLLC(src, self.B, self.pyramid, self.knn)