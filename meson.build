project(
  'c-hashtable',
  'c',
  version: '1.0.0'
)

cc = meson.get_compiler('c')

deps = [
  cc.find_library('m', required : false)
]

headers = [
  'src/hash_table.h',
  'src/prime.h'
]

sources = [
  'src/hash_table.c',
  'src/prime.c'
]

lib = shared_library('libhashtable',
					  sources + headers,
					  dependencies: deps,
					  install: true
					)

executable('c-hashtable', 'src/main.c', link_with: lib)
