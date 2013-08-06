#include <Python.h>
#include <boost/python.hpp>

template<class Key, class Val>
struct map_item
{
    typedef std::map<Key,Val> Map;

    static Val& get(Map const& self, const Key idx) {
      if( self.find(idx) != self.end() ) return self[idx];
      PyErr_SetString(PyExc_KeyError,"Map key not found");
      throw_error_already_set();
    }

    static void set(Map& self, const Key idx, const Val val) { self[idx]=val; }

    static void del(Map& self, const Key n) { self.erase(n); }

    static bool in(Map const& self, const Key n) { return self.find(n) != self.end(); }

    static list keys(Map const& self)
    {
        list t;
        for(auto it=self.begin(); it!=self.end(); ++it)
            t.append(it->first);
        return t;
    }
    static list values(Map const& self)
    {
        list t;
        for(auto it=self.begin(); it!=self.end(); ++it)
            t.append(it->second);
        return t;
    }
    static list items(Map const& self)
    {
        list t;
        for(Map::const_iterator it=self.begin(); it!=self.end(); ++it)
            t.append( make_tuple(it->first, it->second) );
        return t;
    }
};

using namespace boost::python;
typedef std::map<Key,Val> Map;
class_<Map>("Map")
  .def("__len__", &Map::size)
  .def("__getitem__", &map_item<Key,Val>().get, return_value_policy<copy_non_const_reference>() )
  .def("__setitem__", &map_item<Key,Val>().set)
  .def("__delitem__", &map_item<Key,Val>().del)
  .def("clear", &Map::clear)
  .def("__contains__", &map_item<Key,Val>().in)
  .def("has_key", &map_item<Key,Val>().in)
  .def("keys", &map_item<Key,Val>().keys)
  .def("values", &map_item<Key,Val>().values)
  .def("items", &map_item<Key,Val>().items)
  ;
