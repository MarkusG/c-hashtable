htcreate = executable('ht-create',
		   'ht-create.c',
		   include_directories : inc,
		   link_with: lib)
test('create hashtable', htcreate)

htinsertnoresize = executable('ht-insertnoresize',
		   'ht-insert-noresize.c',
		   include_directories : inc,
		   link_with: lib)
test('insert into hashtable (no resize)', htinsertnoresize)

htinsert = executable('ht-insert',
		   'ht-insert.c',
		   include_directories : inc,
		   link_with: lib)
test('insert into hashtable', htinsert)

htsearch = executable('ht-search',
		   'ht-search.c',
		   include_directories : inc,
		   link_with: lib)
test('insert and search', htsearch)

htdelete = executable('ht-delete',
		   'ht-delete.c',
		   include_directories : inc,
		   link_with: lib)
test('delete items', htdelete)
