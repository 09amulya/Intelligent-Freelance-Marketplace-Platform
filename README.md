# Intelligent Freelance Marketplace Platform

A DSA-based freelance marketplace that focuses on intelligently matching projects with suitable freelancers using efficient searching, relationship modelling, scoring, ranking, and Top-K recommendation.

## Project Overview

The platform aims to improve freelancer-project matching beyond simple keyword search. It considers:

- Skills
- Experience
- Rating
- Availability
- Project history
- Rate and budget compatibility

### Basic Workflow

```text
Project Requirements
        ↓
Skill Identification
        ↓
Freelancer Search
        ↓
Candidate Filtering
        ↓
Matching Score
        ↓
Ranking
        ↓
Max Heap / Priority Queue
        ↓
Top-K Recommendations
```

## DSA Concepts

| DSA Concept | Proposed Use |
|-------------|--------------|
| BST / AVL Tree | Efficient searching |
| Hash Map | Fast skill lookup |
| Graph | Freelancer-skill-project relationships |
| BFS / DFS | Exploring related skills |
| Max Heap | Top-K recommendations |
| Sorting | Candidate ranking |

## Initial Graph Model

```text
Freelancer ── HAS_SKILL ──> Skill
Freelancer ── WORKED_ON ──> Project
Project ── REQUIRES ──> Skill
Skill ── RELATED_TO ──> Skill
```

## Matching Approach

The initial matching score is planned around:

```text
Skill Match
+ Experience
+ Rating
+ Availability
+ Budget Compatibility
```

The exact weights will be finalized during implementation.

## Literature Review

The initial research covered four relevant works:

1. **Sahnoun & Elhadjamor (2024)** — *Enhanced Freelance Matching: Integrated Data Analysis and Machine Learning Techniques.*  
   Focus: freelance recommendation and matching.

2. **Jouanneau, Palyart & Jouffroy (2024)** — *Skill Matching at Scale: Freelancer-Project Alignment for Efficient Multilingual Candidate Retrieval.*  
   Focus: skill-based candidate retrieval.

3. **Tu et al. (2017)** — *Gig Services Recommendation Method for Fuzzy Requirement Description.*  
   Focus: gig-service recommendation and requirement matching.

4. **Barnabò et al. (2019)** — *Algorithms for Fair Team Formation in Online Labour Marketplaces.*  
   Focus: algorithmic team formation.

The literature review helped identify **skill matching, efficient candidate retrieval, relationship modelling, ranking, and future team formation** as important directions.

## Current Progress

### Completed

- Problem understanding
- Requirement identification
- DSA Unit 1: Trees
- DSA Unit 2: Graphs
- DSA-to-project mapping
- Initial matching workflow
- Initial graph model
- Literature review
- Conceptual system architecture

### Yet to Implement

- Database
- BST / AVL implementation
- Graph implementation
- Matching algorithm
- Max Heap recommendation
- Frontend and backend
- Testing and performance analysis

## Future Scope

- Explainable recommendations
- Skill graph
- Multi-freelancer team formation
- Dynamic recommendations
- Freelancer skill improvement suggestions
- Project success prediction

## Project Goal

The main goal is to demonstrate how DSA concepts can be applied to a practical marketplace problem and build an efficient recommendation engine instead of creating only a basic freelance marketplace.

**Status:** Month 1 – Problem Understanding, Research & Initial Design  
**Progress:** 25%