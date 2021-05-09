import copy
from typing import List, Tuple, Optional, Iterator
from itertools import combinations

import numpy as np

from config import NULL_FITNESS, MUTATION_INCREASE_STEP, MAX_FITNESS, \
    TOURNAMENT_SIZE_PERCENTAGE, MUTATE_PIXELS_MAX_PERCENTAGE, CROSSOVER_PERCENTAGE, SELECT_OLD_PERCENTAGE, \
    POPULATION_SIZE
from ocr.algorithms.algorithm import OCRAlgorithm
from ocr.gui.painter import Painter
from ocr.utils.fitness import PixelFitnessCalculator
from ocr.utils.plotter import Plotter


class OCRIndividual:
    """Class representing a single individual - combination os chosen pixels"""
    def __init__(self, indexes: np.ndarray, fitness=NULL_FITNESS):
        self.indexes = indexes
        self.fitness = fitness

    def __eq__(self, other):
        return np.array_equal(self.indexes, other.indexes)


class OCRGenetic(OCRAlgorithm):
    """Class for calculation pixel combination using genetic algorithms"""
    def __init__(self, pixel_count: int, indexes_array: np.ndarray,
                 fitness_calculator: PixelFitnessCalculator,
                 plotter: Plotter, painter: Painter, seed: Optional[int],
                 population_size: int, generations_count: int):
        super().__init__(pixel_count, indexes_array, fitness_calculator,
                         plotter, painter, seed, population_size, generations_count)
        self.population: List[OCRIndividual] = []
        self.mutation_probability = 1 / float(pixel_count)
        self.mutate_swap_count = 0
        self.pixel_combinations_generator: Optional[Iterator[Tuple[int, ...]]] = None

    def get_new_pixel_combination(self) -> OCRIndividual:
        generation_array_indexes = np.random.choice(len(self.indexes_array),
                                                    size=self.pixel_count,
                                                    replace=False)
        new_generation = self.indexes_array[generation_array_indexes]
        return OCRIndividual(new_generation)

    def create_first_generation(self):
        population = []

        for _ in range(self.population_size):
            combination_array_indexes = np.random.choice(len(self.indexes_array),
                                                         size=self.pixel_count,
                                                         replace=False)
            new_combination = self.indexes_array[combination_array_indexes]
            population.append(OCRIndividual(new_combination))
        self.population = population

    def create_first_generation_old(self):
        """Creates an initial generation of randomly generated combinations of pixels"""

        # randomly shuffles array of indexes
        self.shuffle_index_array(self.indexes_array, self.seed)

        # creates iterator which can generate all possible combinations of a given length
        self.pixel_combinations_generator = combinations(self.indexes_array, self.pixel_count)

        population = []
        # generates new index combinations
        # for index_combination in (np.array(comb) for comb in self.pixel_combinations_generator):
        for _ in range(self.population_size):
            # calculated_fitness \
            #     = self.fitness_calculator.calculate_fitness(indexes_array=index_combination)
            population.append(self.get_new_pixel_combination())

            # comb_count += 1
            # if comb_count >= self.population_size:
            #     break

        # if comb_count < self.population_size:
        #     raise Exception("Population size cannot be large than number of pixels")

        self.population = population

    def recalculate_fitness(self):
        """Calculates fitness for each individual in a new generations"""
        for individual in self.population:
            individual.fitness = self.fitness_calculator.calculate_fitness(individual.indexes)

        self.population.sort(key=lambda x: x.fitness, reverse=True)

    def select(self):
        """Selects individual combinations of indexes from\
         the old generation using the tournament selection."""
        tournament_size = int(self.population_size*TOURNAMENT_SIZE_PERCENTAGE)

        new_generation = []
        for _ in range(self.population_size):

            if SELECT_OLD_PERCENTAGE < np.random.uniform():
                new_generation.append(self.get_new_pixel_combination())
                continue

            chosen_individual_indexes = tuple(np.random.choice(self.population_size, tournament_size))
            chosen_individuals = [self.population[x] for x in chosen_individual_indexes]
            best_individual = max(chosen_individuals, key=lambda x: x.fitness)

            new_generation.append(copy.deepcopy(best_individual))
            # new_generation.append(OCRIndividual(indexes=np.copy(best_individual.indexes)))

        self.population = new_generation

    def crossover(self):
        """Crosses over each two individual pixel combinations"""

        child_generation = []

        for i in range(self.population_size):
            j = i-1

            if CROSSOVER_PERCENTAGE < np.random.uniform():
                child_generation.append(self.population[i])
                continue
                # pass

            concatenated_array = np.concatenate((self.population[i].indexes,
                                                 self.population[j].indexes))
            available_indexes_array = np.unique(concatenated_array, axis=0)
            new_array_indexes = np.random.choice(len(available_indexes_array),
                                                 size=self.pixel_count,
                                                 replace=False)
            new_array = available_indexes_array[new_array_indexes]

            child_generation.append(OCRIndividual(new_array))

        self.population = child_generation

    def mutate(self):
        """Randomly mutates individuals by replacing pixels"""

        # goes thought entire populations
        for individual in self.population:
            if self.mutation_probability < np.random.uniform():
                continue

            for _ in range(np.random.choice(int(self.pixel_count * MUTATE_PIXELS_MAX_PERCENTAGE), 1)[0]):
                for index_new in (np.random.choice(len(self.indexes_array), 1) for x in range(len(self.indexes_array))):
                    # replaces pixels if not already present in pixel combination
                    if self.indexes_array[index_new] not in individual.indexes:
                        index_old = np.random.choice(self.pixel_count, 1)
                        individual.indexes[index_old] = self.indexes_array[index_new]
                        self.mutate_swap_count += 1
                        break

    def calculate_for_k_pixels(self) -> Tuple[bool, np.ndarray]:
        """Uses genetic algorithm to find a combination of pixels."""
        self.population = []

        self.create_first_generation()
        self.recalculate_fitness()

        best_fitness = self.population[0].fitness
        last_fitness = self.population[0].fitness
        best_combination = self.population[0].indexes

        for _ in range(self.generations_count):
            # selection
            self.select()

            # crossover
            self.crossover()

            # mutate
            self.mutate()

            # recalculate
            self.recalculate_fitness()

            # get best combinations of current generation
            fitness = self.population[0].fitness

            # generation_all_fitness = [individual.fitness for individual in self.population]
            self.plotter.add_record(fitness)
            self.painter.change_chosen_pixels(self.population[0].indexes)

            if last_fitness > fitness:
                self.mutation_probability += MUTATION_INCREASE_STEP
            last_fitness = fitness

            # check if fitness has improved
            if best_fitness == NULL_FITNESS or fitness > best_fitness:
                best_fitness = fitness
                best_combination = self.population[0].indexes.copy()

                # stop when desired final solution has been found
                if best_fitness == MAX_FITNESS:
                    print("Found best fitness")
                    break

        print(f"For {self.pixel_count} pixels, mutation swap count: {self.mutate_swap_count}")
        print(f"Best fitness: {best_fitness}")
        print(f"Mutation probability: {self.mutation_probability}")
        return best_fitness == MAX_FITNESS, best_combination
