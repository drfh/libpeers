project('libpeers', 'c',
	default_options : [
		'warning_level=3',
		'werror=false',
		'debug=false',
		'optimization=0',
		'c_std=c11', 'build.c_std=c11'
		],
	license: 'UNLICENSE',
	version: '0.0.1',
)
project_description = 'A p2p messaging library.'

# ======
# Target
# ======
incdir = include_directories('./globals/','./include/','./util/','/usr/include/','/usr/local/include/')

project_headers = [
	'globals/global.h'

]

project_source_files = [
	'source/peers.c'
	# ,'src/socks.c'
	# ,'src/node.c'
# ,'src/message.c'
# ,'src/messagequeue.c'
# ,'src/ip.c'
]

public_headers = include_directories('include')

# libsodium_lib = meson.get_compiler('c').find_library('libsodium')
# if (libsodium_lib.found())
#     libsodium_dep = declare_dependency(
#         dependencies : libsodium_lib,
#         link_args :  get_option('sodium_link_args'))
#     config_h.set('HAVE_SODIUM', 1, description : 'Whether to use libsodium for cryptography.')
# else
#     libsodium_dep = dependency('', required: false)
# endif

dependencies=[
	dependency('threads')
	,dependency('libcjson')
	,dependency('libconfig')
	,dependency('libcutil')
	# ,dependency('glib-2.0')
	# ,dependency('libcrypt')
	# ,dependency('libsodium')
	# ,dependency('libxxhash')
]

project_target=shared_library('libpeers', project_source_files,include_directories:incdir,dependencies:dependencies)

# =======
# Project
# =======
# Make this library usable as a Meson subproject.
project_dep = declare_dependency(
	include_directories: public_headers,
	link_with : project_target
)
set_variable(meson.project_name() + '_dep', project_dep)
if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('libpeers', project_dep)
endif


# Make this library usable from the system's package manager.
install_headers(project_headers, subdir : meson.project_name())

pkg_mod = import('pkgconfig')
pkg_mod.generate(
	name : meson.project_name(),
	filebase : meson.project_name(),
	description : project_description,
	subdirs : meson.project_name(),
	libraries : project_target,
)

if not meson.is_subproject()
	if get_option('unit-tests')
		subdir('tests')
	endif

endif
