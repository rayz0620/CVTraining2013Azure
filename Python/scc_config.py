from os import path
from matrixio import io
matIO = io()

basePath = '/home/rayz/dataset'
imgPath = path.join(basePath, 'images')
featPath = path.join(basePath, 'imgFeat')
cfgPath = path.join(basePath, 'config')
featCfg = path.join(cfgPath, "feaConfig.yml")
llcCfg = path.join(cfgPath, "llcConfig.yml")
scCfg = path.join(cfgPath, "scConfig.yml")
mainDB = path.join(basePath, 'mainDB')
semDB = path.join(basePath, 'subDB')
llcBase = matIO.load(path.join(cfgPath, 'llcBase.yml'))
llcPyramid = matIO.load(path.join(cfgPath, 'llcPyramid.yml'))