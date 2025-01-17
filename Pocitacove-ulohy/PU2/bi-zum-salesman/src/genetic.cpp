//---------------------------------------------------------------------------
//
//  Template for solving the Travelling Salesman Problem
//  (c) 2021 Ladislava Smítková Janků <ladislava.smitkova@fit.cvut.cz>
//
//  genetic.cpp: Implementation of genetic algorithm with these parameters:
//
//  Population:        500 individuals (can be modified by POPULATION constant)
//  Generations:       30 (can be modified by GENERATIONS constant)
//  Crossover method:  OX or PMX
//  Mutation method:   reversion of the path
//
//  Crossover probability:    95%  (PROBABILITY_CROSSOVER)
//  Mutation probability:     stepped by 5%  (PROBABILITY_MUT_STEP)
//
//  If the fitness value of the actual generation is better than last one,
//  mutation probability will be set to zero. In other case, mutation
//  probability will be increased by PROBABILITY_MUT_STEP.
//
//---------------------------------------------------------------------------

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <climits>
#include <algorithm>
#include <set>
#include <unordered_set>

#include "genetic.h"
#include "path.h"

#define POPULATION              100
#define PROBABILITY_CROSSOVER   0.95
#define PROBABILITY_MUT_STEP    0.05
#define GENERATIONS             200

typedef struct {
    std::vector<int> path;
    long long fitness;
    double Pr;
    double q;
} TIndividual;

std::vector<TIndividual> individuals;

bool compareByFitness(const TIndividual &a, const TIndividual &b) {
    return a.fitness > b.fitness;
}

long long computeFitness(const std::vector<int> &path, TMatrix *matrix) {
    // Fitness Function (also known as the Evaluation Function) evaluates how close
    // a given solution is to the optimum solution of the desired problem.
    // It determines how fit a solution is.
//    double fitness = ((double) 1) / calculatePathLength(path, matrix);
    long long fitness = -calculatePathLength(path, matrix);
    return fitness;
}

void recalculate(TMatrix *matrix) {
    // calculate fitness and Pr
    long long sum_fitness = 0;
    for (auto &individual : individuals) {
        individual.fitness = computeFitness(individual.path, matrix);
        sum_fitness += individual.fitness;
    }

    // sort population by fitness
    std::sort(individuals.begin(), individuals.end(), compareByFitness);

    // compute Pr_i and q_i
    double q = 0;
    for (auto &individual : individuals) {
        individual.Pr = (double) individual.fitness / (double) sum_fitness;
        q += individual.Pr;
        individual.q = q;
    }
}

void selection(TCrossoverMethod crossoverMethod) {
    std::vector<TIndividual> newGeneration;

    //if the crossover method is ERX, then selection generates 2x bigger population
    int outputPopulationSize = POPULATION;
    if (crossoverMethod == CROSSOVER_METHOD_ERX) {
        outputPopulationSize *= 2;
    }

    for (int i = 0; i < outputPopulationSize; i++) {
        std::set<int> tournament;

        for (int j = 0; j < 5; j++) {
//            for (int j = 0; j <=  (rand() % (POPULATION/2)); j++) {
            tournament.insert(rand() % POPULATION);
        }
        newGeneration.emplace_back(individuals[*tournament.begin()]);
    }

    // new generation was born
    individuals = newGeneration;
}

bool pathContainsCity(const std::vector<int> &path, int city) {
    for (int x : path) {
        if (city == x) return true;
    }
    return false;
}

void doCrossoverOX(std::vector<TIndividual> &result, TMatrix *, TIndividual &a, TIndividual &b) {
    TIndividual aa, bb;

    aa = a;
    bb = b;

    std::vector<int> newPathA;
    std::vector<int> newPathB;

    int citiesNum = a.path.size();

    //computing slice locations
    int sliceLow = rand() % (citiesNum - 1);
    int sliceHigh = (rand() % (citiesNum - sliceLow + 1)) + sliceLow;

    //insert middle part of genome
    newPathA.insert(newPathA.begin(), a.path.begin() + sliceLow, a.path.begin() + sliceHigh);
    newPathB.insert(newPathB.begin(), b.path.begin() + sliceLow, b.path.begin() + sliceHigh);

    int currentIndex;
    int currentCityA = 0;
    int currentCityB = 0;

    //insert the rest of cities in ordered crossover
    for (int i = 0; i < citiesNum; i++) {
        currentIndex =
                (sliceHigh + i) % citiesNum; //gets current city index. Allows to "go around" the array of cities.
        currentCityA = a.path[currentIndex];
        currentCityB = b.path[currentIndex];


        // insert current city from the other path, if not already present
        if (!pathContainsCity(newPathA, currentCityB)) {
            newPathA.emplace_back(currentCityB);
        }
//        insertCityIfNotPresent(newPathA, currentCityB);


        if (!pathContainsCity(newPathB, currentCityA)) {
            newPathB.emplace_back(currentCityA);
        }
//        insertCityIfNotPresent(newPathB, currentCityA);
    }

    //rotates paths so that the middle part is in the correct place
//    std::rotate(newPathA.begin(), newPathA.begin() + sliceLow, newPathA.end());
//    std::rotate(newPathB.begin(), newPathB.begin() + sliceLow, newPathB.end());
    std::rotate(newPathA.begin(), newPathA.end() - sliceLow, newPathA.end());
    std::rotate(newPathB.begin(), newPathB.end() - sliceLow, newPathB.end());


    aa.path = newPathA;
    bb.path = newPathB;

    // propagate only children
    result.push_back(aa);
    result.push_back(bb);
}

void doCrossoverPMX(std::vector<TIndividual> &result, TMatrix *, TIndividual &a, TIndividual &b) {

    TIndividual aa, bb;

    aa = a;
    bb = b;

    std::vector<int> newPathA;
    std::vector<int> newPathB;

    int citiesNum = a.path.size();

    //computing slice locations
    int sliceLow = rand() % (citiesNum - 1);
    int sliceHigh = (rand() % (citiesNum - sliceLow + 1)) + sliceLow;

    //insert middle part of genome
    newPathA.insert(newPathA.begin(), a.path.begin() + sliceLow, a.path.begin() + sliceHigh);
    newPathB.insert(newPathB.begin(), b.path.begin() + sliceLow, b.path.begin() + sliceHigh);

    std::unordered_map<int, int> mapAtoB;
    std::unordered_map<int, int> mapBtoA;

    for (size_t i = 0; i < newPathA.size(); i++) {
        mapAtoB.insert({newPathA[i], newPathB[i]});
        mapBtoA.insert({newPathB[i], newPathA[i]});
    }

    int currentIndex;
    int currentCityA = 0;
    int currentCityB = 0;

    //insert the rest of cities in PMX crossover
    for (int i = 0; i < citiesNum /*- (sliceHigh - sliceLow)*/; i++) {
        currentIndex =
                (sliceHigh + i) % citiesNum; //gets current city index. Allows to "go around" the array of cities.
        currentCityA = a.path[currentIndex];
        currentCityB = b.path[currentIndex];

        // insert current city from the other path, if not already present
        if (!pathContainsCity(newPathA, currentCityB)) {
            newPathA.emplace_back(currentCityB);
        }
            // inserts current city from the other path substituted for a different city from the other path
        else if (mapAtoB.find(currentCityB) != mapAtoB.end() && !pathContainsCity(newPathA, mapAtoB.at(currentCityB))) {
            newPathA.emplace_back(mapAtoB.at(currentCityB));
        }


        if (!pathContainsCity(newPathB, currentCityA)) {
            newPathB.emplace_back(currentCityA);
        } else if (mapBtoA.find(currentCityA) != mapBtoA.end() &&
                   !pathContainsCity(newPathB, mapBtoA.at(currentCityA))) {
            newPathB.emplace_back(mapBtoA.at(currentCityA));
        }
    }

    //rotates paths so that the middle part is in the correct place
    std::rotate(newPathA.begin(), newPathA.end() - sliceLow, newPathA.end());
    std::rotate(newPathB.begin(), newPathB.end() - sliceLow, newPathB.end());


    aa.path = newPathA;
    bb.path = newPathB;

    // propagate only children
    result.push_back(aa);
    result.push_back(bb);
}

void doCrossoverERX(std::vector<TIndividual> &result, TMatrix *, TIndividual &a, TIndividual &b) {

    TIndividual aa;
    aa = a;
    std::vector<int> newPath;

    //contains elements that are still not on final path
    std::set<int> notOnNewPath;
    for (auto i : a.path) {
        notOnNewPath.insert(i);
    }

    //pathLength
    size_t citiesNum = a.path.size();

    std::unordered_map<int, std::set<int>> neighbours;

    //inserts neighbours for cities
    for (size_t i = 0; i < citiesNum - 1; i++) {
        neighbours[a.path[i]].insert(a.path[i + 1]);
        neighbours[b.path[i]].insert(b.path[i + 1]);
    }
    //inserts neighbors from the other side of paths
    neighbours[a.path[0]].insert(a.path[citiesNum - 1]);
    neighbours[b.path[0]].insert(b.path[citiesNum - 1]);
    neighbours[a.path[citiesNum - 1]].insert(a.path[0]);
    neighbours[b.path[citiesNum - 1]].insert(b.path[0]);

//    int currentIndex = 0;
    int currentCity = 0;

    //randomly pics first city from path A or B
    if (rand() % 2 == 1) {
        currentCity = a.path[0];
    } else {
        currentCity = b.path[0];
    }

    //insert the the cities in ERX crossover
    while (true) {
        //insert city on path
        newPath.emplace_back(currentCity);
        notOnNewPath.erase(currentCity);

        //end cycle if all cities are on the final path
        if (newPath.size() == citiesNum) {
            break;
        }

        //erases this city as a neighbour from other cities
        for (size_t j = 0; j < citiesNum; j++) {
            neighbours[j].erase(currentCity);
        }

        if (!neighbours[currentCity].empty()) {
            //pick random element from current city's neighbours
            currentCity = *std::next(std::begin(neighbours[currentCity]), rand() % neighbours[currentCity].size());
        } else {
            //pick random city, not in newPath. (notOnNewPath is unordered_set, so 1st element is picked on "random")
            currentCity = *std::next(std::begin(notOnNewPath), rand() % notOnNewPath.size());
        }

    }

    aa.path = newPath;
    // propagate only child
    result.push_back(aa);
}

void crossover(TMatrix *matrix, TCrossoverMethod crossoverMethod) {
    std::vector<TIndividual> crossovered;
    std::vector<TIndividual>::iterator candidate = individuals.end();

    for (auto ind = individuals.begin(); ind != individuals.end(); ++ind) {
        // select candidates to the crossover process
        if (drand48() <= PROBABILITY_CROSSOVER) {
            if (candidate == individuals.end()) {
                // this is the first parent
                candidate = ind;
            } else {
                // now we have both parents, we can do crossover
                if (crossoverMethod == CROSSOVER_METHOD_PMX)
                    doCrossoverPMX(crossovered, matrix, *ind, *candidate);
                else if (crossoverMethod == CROSSOVER_METHOD_OX)
                    doCrossoverOX(crossovered, matrix, *ind, *candidate);
                else
                    doCrossoverERX(crossovered, matrix, *ind, *candidate);

                candidate = individuals.end();
            }
        } else
            crossovered.push_back(*ind);
    }

    // If we got odd number of parents, do nothing with this candidate and push it directly
    // into the new generation.
    if (candidate != individuals.end())
        crossovered.push_back(*candidate);

    // crossover is done
    individuals = crossovered;
}

void randomPermutationMutation(TIndividual &individual) {
    for (int i = 0; i <= (int) (rand() % (individual.path.size() / 2)); i++) {
        int a = (rand() % (individual.path.size() / 2));
        int b = (rand() % (individual.path.size() / 2));
        int tmp = individual.path[a];
        individual.path[a] = individual.path[b];
        individual.path[b] = tmp;
    }
}

void mutation(double probability) {
    for (auto &individual : individuals) {
        if (drand48() <= probability) {
            //swaps random amount of value pairs
            randomPermutationMutation(individual);
        }
    }
}

void printState(int generation) {
    printf("[%d]  %lld\n", generation, -individuals.at(0).fitness);
}

std::vector<int> salesmanProblemGenetic(TMatrix *matrix, TCrossoverMethod crossoverMethod) {
    unsigned i, j;
    int x;
    std::vector<int>::iterator p;
    double mutation_probability = 0;
    long long lastFitness = LLONG_MIN;
    std::vector<int> best;
    long long bestFitness = LLONG_MIN;

    // initialization of random number generator
    srand(getpid());
    //todo change to c++ way

    // born first population
    for (i = 0; i < POPULATION; i++) {
        TIndividual ind;

        // Generate some random path: Place city indexes to the vector in some random order.
        // At index 0 will be city we start from.
        ind.path.clear();
        ind.path.push_back(0);
        j = 1;
        while (j < matrix->getNumberOfTargets()) {
            x = random() % matrix->getNumberOfTargets();
            p = find(ind.path.begin(), ind.path.end(), x);
            if (p == ind.path.end()) {
                ind.path.push_back(x);
                j++;
            }

        }

        // Store this path into table of individuals.
        // Fitness and other parameters will be computed later.
        individuals.push_back(ind);
    }

    // compute fitnesses and sort individuals
    recalculate(matrix);
    printState(0);

    // remember the best solution
    best = individuals.at(0).path;
    bestFitness = individuals.at(0).fitness;

    // run simulation
    for (i = 1; i < GENERATIONS; i++) {
        // selection: select individuals for a new generation
        selection(crossoverMethod);

        // crossover
        crossover(matrix, crossoverMethod);

        // mutation
        if (mutation_probability > 0) mutation(mutation_probability);

        // print the best result
        recalculate(matrix);

        printState(i);

        // if fitness < lastFitness, increase mutation probability by one step
        if (individuals.at(0).fitness < lastFitness) {
            mutation_probability += PROBABILITY_MUT_STEP;
        } else {
            mutation_probability = 0;
        }

        lastFitness = individuals.at(0).fitness;

        if (lastFitness > bestFitness) {
            best = individuals.at(0).path;
            bestFitness = individuals.at(0).fitness;
        }
    }

    return best;
}
