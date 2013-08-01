import llcoder
import matrixio as io
import FeatureDatabase as fdb

cfg = '127_0005.yml'
i = io.io()
y = i.load("qfea.yml")
#print y
i.save("1.yml", y)
#y = io.load(cfg)

c = llcoder.LLCoder()
c.loadConfig(cfg)b
print y
#print c.pyramid
#print c.knn
