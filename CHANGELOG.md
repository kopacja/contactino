# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.0.2] - 2016-12-02

### Added

- 2D two-node linear segments
- Distinguishing the normal vector in the initial (for integration) and current (for kinematics) configuration
- Introduction of a Boolean value to indicate an active/inactive integration point
- 

### Fixed

- In addition to the C_m array, initialize also the C_s array with zeros

### Changed

- The tangential contact matrix constructed instead of the upper triangle as a full symmetrized matrix

## [0.0.1] - 2016-11-29

### Added

- Contact Gausspint data in table GPs
- GPTS frictionless penalty two-half-pass formulation
- Only sfd6() i.e. quadratic triangle contact element in 3D
- All arrays are 1D

[unreleased]: https://github.com/kopacja/contactino/compare/v0.0.2...HEAD
[0.0.2]: https://github.com/kopacja/contactino/releases/tag/v0.0.2
[0.0.1]: https://github.com/kopacja/contactino/releases/tag/v0.0.1