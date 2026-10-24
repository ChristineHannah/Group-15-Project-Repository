# Individual Progress Report - Week 03

**Name:** TANGA IBRAHIM  
**Role:** Feature Expansion & Data Preprocessing

## 1. Summary of Completed Deliverables

- Implemented the C++ source logic inside `src/feature_expansion.cpp` corresponding to the header declared in Week 1.
- Verified compilation cleanly using the project's CMake build configuration.
- Passed local unit tests associated with polynomial feature expansion, including boundary edge-cases.

## 2. Object-Oriented Class Breakdown & Architectural Narrative

### Module Implementation and Purpose

The development work this week focused on the implementation of the `FeatureExpansion` class, which is declared inside `include/poly_reg/feature_expansion.hpp` and defined within `src/feature_expansion.cpp`.

The primary objective of this class is to isolate and automate the mathematical process of mapping input datasets into higher-dimensional polynomial feature spaces. By expanding features up to a configured degree *d* and appending a baseline bias/intercept term, the module transforms standard linear inputs into structural representations capable of capturing non-linear relationships.

### Data Storage Strategy and Interface Design

The `FeatureExpansion` class acts as a stateless service utility layer within the machine learning pipeline. It holds no internal private data attributes. Instead, it relies on incoming data references, processing raw information structures via functional composition using `const Matrix& input_feature_matrix`.

Operations are handled strictly through the static public utility function `create_polynomial_features(const Matrix& input_feature_matrix, int polynomial_degree)`. This function is responsible for processing boundary input validations, easily instantiating target matrices, tracking exponent indexing across configurations, and executing row-by-row matrix expansions.

Below are the illustrations of the system;
![hand drawn system illstrations](<IMG_20261024_161519 report week 3.jpg>)



### Encapsulation and System Integration

The core interface method is exposed as a public static function to grant external pipeline modules direct access to the feature engineering engine. Because it is stateless, other modules can convert data matrices instantaneously without managing object lifecycles. All internal index manipulation and mathematical indexing remain enclosed within the local scope of the function execution block, preventing external corruption and ensuring structural decoupling across the program.

## 3. Challenges & Solutions

- **Challenge:** Handling input anomalies, such as empty datasets or invalid polynomial degree configurations (e.g., negative integers or zero values), which would lead to out-of-bounds array access and segmentation faults during matrix expansion.
- **Solution:** Integrated early-exit boundary validations at the entry point of the expansion sequence.

## 4. AI Tool Transparency

- **Tool Used:** Gemini was used in generation of the illustrations in the report to show feature expansion in data matrix feature expansion and data preprocessing.
