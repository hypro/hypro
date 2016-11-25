__AUTHOR__="Stefan Schupp"

echo 'Starting coverage script ...'

if [ "${FLAGS}" == "-DHYPRO_COVERAGE=ON" ]; then
	echo 'Collecting files ...'
	lcov --directory . --capture --output-file coverage.info # capture coverage info
	lcov --remove coverage.info 'tests/*' '/usr/*' --output-file coverage.info # filter out system and test code
	lcov --list coverage.info # debug before upload
	echo 'Upload files ...'
	coveralls-lcov --repo-token ${COVERALLS_TOKEN} coverage.info # uploads to coveralls
fi

echo 'Coverage done.'
