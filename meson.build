project(
  'c-hashtable',
  'c',
  version: '1.0.0'
)

cc = meson.get_compiler('c')

deps = [
  cc.find_library('m', required : false)
]

inc = include_directories('include')

subdir('include')
subdir('src')
subdir('test')
