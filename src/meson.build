sources = [
  'hash_table.c',
  'prime.c'
]

headers = [
  'prime.h'
]

lib = shared_library(
  'hashtable',
  sources + headers,
  dependencies: deps,
  include_directories : inc,
  install: true
)
