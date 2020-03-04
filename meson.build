project(
	'paulstretch',
	'c',
	version: '0.0.0',
	license: 'MIT',
	default_options: [
		'c_std=c11',
		'warning_level=3',
		'werror=true',
	],
)

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
	'-Wno-missing-braces',
	'-Wno-unused-parameter',
]), language: 'c')

paulstretch_inc = include_directories('include')

fftw = dependency('fftw3f')
m = cc.find_library('m', required: false)

paulstretch_deps = [fftw, m]

paulstretch_lib = library(
	meson.project_name(),
	files(
		'paulstretch.c',
	),
	include_directories: paulstretch_inc,
	version: meson.project_version(),
	dependencies: paulstretch_deps,
	install: true,
)

paulstretch = declare_dependency(
	link_with: paulstretch_lib,
	include_directories: paulstretch_inc,
	dependencies: paulstretch_deps,
)

install_headers('include/paulstretch.h')

pkgconfig = import('pkgconfig')
pkgconfig.generate(
	libraries: paulstretch_lib,
	version: meson.project_version(),
	filebase: meson.project_name(),
	name: meson.project_name(),
	description: 'Audio stretching library',
)

subdir('example')
