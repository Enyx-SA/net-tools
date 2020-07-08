# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Changed
- Session configurations can be read from stdin
### Added
- Sphinx documentation

## [1.0.0] - 2019-09-06
### Added
- Multiple sessions handling
### Changed
- Accept sessions parameters from response file
- Rename nx-iperf to `enyx-net-tester`

## [0.1.7] - 2019-04-25
### Fixed
- `-S` argument used for both `datagram-size` and `shutdown-policy`

## [0.1.6] - 2019-03-29
### Added
-  `--max-datagram-size` argument

## [0.1.5] - 2019-01-25
### Changed
- Allow UDP reception from any source

## [0.1.4] - 2019-01-21
### Fixed
- UDP bandwidth computing

## [0.1.3] - 2018-10-27
### Changed
- Return the POSIX error as process exit status.

## [0.1.2] - 2018-10-16
### Addded
- UDP Protocol