import scc_config as cfg
import FeatureDatabase as fdb
import LLCoder as LLC
import IOUtils



def preprocessQuery(queryFilename):
	#Initialize objects and load config
	db = fdb.FeatureDatabase()
	db.loadConfig(cfg.featCfg)

	llc = LLC.LLCoder()
	llc.loadConfig(cfg.llcCfg)

	return db.calculateItem(queryFilename)