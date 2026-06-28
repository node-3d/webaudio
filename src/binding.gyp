{
	'variables': {
		'bin': '<!(node -e "import(\'@node-3d/addon-tools\').then((m) => m.printBin())")',
		'ls_include': '<!(node -p "require(\'@node-3d/deps-labsound\').include")',
		'ls_bin': '<!(node -p "require(\'@node-3d/deps-labsound\').bin")',
	},
	'targets': [{
		'target_name': 'webaudio',
		'includes': ['common.gypi'],
		'sources': [
			'cpp/bindings.cpp',
		],
		'include_dirs': [
			'<(ls_include)',
			'<!@(node -e "import(\'@node-3d/addon-tools\').then((m) => m.printInclude())")',
		],
		'library_dirs': ['<(ls_bin)'],
		'conditions': [
			['OS=="linux"', {
				'cflags_cc!': ['-fno-rtti', '-fno-exceptions'],
				'cflags_cc': ['-w', '-frtti', '-fexceptions'],
				'libraries': [
					"-Wl,-rpath,'$$ORIGIN'",
					"-Wl,-rpath,'$$ORIGIN/../node_modules/@node-3d/deps-labsound/<(bin)'",
					"-Wl,-rpath,'$$ORIGIN/../../@node-3d/deps-labsound/<(bin)'",
					'-lLabSound', '-llibnyquist', '-lasound',
				],
			}],
			['OS=="mac"', {
				'cflags_cc!': ['-fno-rtti', '-fno-exceptions'],
				'cflags_cc': ['-w', '-frtti', '-fexceptions'],
				'libraries': [
					'-Wl,-rpath,@loader_path',
					'-Wl,-rpath,@loader_path/../node_modules/@node-3d/deps-labsound/<(bin)',
					'-Wl,-rpath,@loader_path/../../@node-3d/deps-labsound/<(bin)',
					'-llibnyquist',
					'-L<(ls_bin)',
					'<(ls_bin)/LabSound',
				],
				'xcode_settings': {
					'DYLIB_INSTALL_NAME_BASE': '@rpath',
					'GCC_ENABLE_CPP_RTTI': 'YES',
					'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
					'OTHER_LDFLAGS': [
						'-framework AudioUnit',
						'-framework CoreAudio',
						'-framework AudioToolbox',
					],
					'OTHER_CPLUSPLUSFLAGS!': ['-fno-rtti', '-fno-exceptions'],
					'OTHER_CPLUSPLUSFLAGS': ['-w', '-frtti', '-fexceptions'],
				},
			}],
			['OS=="win"', {
				'libraries': [
					'-lwinmm', '-luser32', '-lLabSound', '-llibnyquist',
				],
				'defines!': ['_HAS_EXCEPTIONS=0'],
				'msvs_settings': {
					'VCCLCompilerTool': {
						'ExceptionHandling': '1',
						'AdditionalOptions!': ['/EHa-s-c-', '/GR-'],
						'AdditionalOptions': ['/EHsc', '/GR'],
					},
				},
			}],
		],
	}]
}
