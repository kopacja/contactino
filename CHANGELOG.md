# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.6] - 2020-03-30

### Added

- Distinguishing between master and slave normal vector

## [0.0.5] - 2019-10-25

### Added

- sfd4() i.e. four-node quad contact element in 3D
- Support of friction using epsN, epsT and mu
- npd (=Number of Parametric Dimensions)
- Support of axisymmetry using isAxisymmetric key
- Max penetration less then constant 25

### Fixed

- Skip the Gausspoint of the linkedList if its segment index is equal to the master's one

### Changed

- master element/segment index moved in GPs table
- (GAPs[g] > 0.0) changed to (GAPs[g] < -1e-8)

## [0.0.4] - 2017-08-22

### Added

- Doxygen comments
- Export of Gc_cols and Kc

### Fixed

- Removed inner loop through spatial coordinates in AABB calculation
- Removed "inflating" AABB by half the longestEdge

### Changed

- longestEdge calculated as the longest distance between all nodes of the segment
- The distance calculated as a projection onto the triangle is refined in the local search

## [0.0.3] - 2017-01-22

### Added

- Key keyAssembleKc indicating the requirement to assemble Kc
- sfd8() i.e. eigth-node quad contact element in 3D

### Fixed

- Update the master element and segment number for each slave integration point

### Changed

- activeGPs changed from double to bool
- (GAPs[g] > 1e-4) changed to (GAPs[g] > 0.0)
- Only values greater than 1e-50 in absolute value are assembled
- If the contact segment of an element is a quadrilateral, it is divided into 4 triangles
- max_niter changed from 100 to 1000 in the local contact searching
- Store master element end segment index and r,s coords only if d < 0

## [0.0.2] - 2016-12-02

### Added

- 2D two-node linear segments
- Distinguishing the normal vector in the initial (for integration) and current (for kinematics) configuration
- Introduction of a Boolean value to indicate an active/inactive integration point

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

[unreleased]: https://github.com/kopacja/contactino/compare/v0.0.6...HEAD
[0.0.6]: https://github.com/kopacja/contactino/releases/tag/v0.0.5
[0.0.5]: https://github.com/kopacja/contactino/releases/tag/v0.0.5
[0.0.4]: https://github.com/kopacja/contactino/releases/tag/v0.0.4
[0.0.3]: https://github.com/kopacja/contactino/releases/tag/v0.0.3
[0.0.2]: https://github.com/kopacja/contactino/releases/tag/v0.0.2
[0.0.1]: https://github.com/kopacja/contactino/releases/tag/v0.0.1