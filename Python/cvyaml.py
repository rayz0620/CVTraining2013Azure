import yaml
import numpy as np
def opencv_matrix(loader, node):
    mapping = loader.construct_mapping(node)
    mat = np.array(mapping["data"])
    mat.resize(mapping["rows"], mapping["cols"])
    return mat
yaml.add_constructor(u"tag:yaml.org,2002:opencv-matrix", opencv_matrix)

def load(file):
	return yaml.load(file)