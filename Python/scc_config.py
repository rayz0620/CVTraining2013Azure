from matrixio import io
matIO = io()

basePath = './'
imgPath = basePath + 'images/'
featPath = basePath + 'imgFeat/'
cfgPath = basePath + 'config/'
featCfg = cfgPath + "feaConfig.yml"
llcCfg = cfgPath + "llcConfg.yml"
scCfg = cfgPath + "scConfig.yml"

llcBase = matIO.load(cfgPath + 'llcBase.yml')
llcPyramid = matIO.load(cfgPath + 'llcPyramid.yml')



