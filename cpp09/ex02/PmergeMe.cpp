#include "PmergeMe.hpp"

#include <cstddef>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &) { return *this; }
PmergeMe::~PmergeMe() {}

static std::size_t jacobsthal(std::size_t n) // J(n) = (2^n - (-1)^n) / 3
{
  return ((1UL << n) - 1UL + ((n & 1UL) << 1)) / 3UL;
}

namespace VectorSort {
typedef std::vector<struct NumberNode *> NumberNodeVec;
struct NumberNode {
  int number;
  NumberNodeVec inferiors;
  std::size_t chainPosition;
  NumberNode(int n = 0) : number(n), chainPosition(0) {}
};

static std::size_t binaryInsert(NumberNodeVec &chain, NumberNode *element,
                                std::size_t upperBound) {
  std::size_t insertPosition = 0;

  while (insertPosition < upperBound) {
    std::size_t middle = insertPosition + (upperBound - insertPosition) / 2;

    if (chain[middle]->number < element->number)
      insertPosition = middle + 1;
    else
      upperBound = middle;
  }
  chain.insert(chain.begin() + insertPosition, element);
  return insertPosition;
}

static NumberNodeVec mergeInsertionSort(const NumberNodeVec &numbers) {
  if (numbers.size() <= 1)
    return numbers;

  NumberNodeVec superiors;
  NumberNode *stray = NULL;

  if (numbers.size() % 2 != 0)
    stray = numbers.back();

  for (std::size_t i = 0; i + 1 < numbers.size(); i += 2) {
    NumberNode *superior;
    NumberNode *inferior;

    if (numbers[i]->number < numbers[i + 1]->number) {
      superior = numbers[i + 1];
      inferior = numbers[i];
    } else {
      superior = numbers[i];
      inferior = numbers[i + 1];
    }
    superior->inferiors.push_back(inferior);
    superiors.push_back(superior);
  }

  NumberNodeVec mainChain = mergeInsertionSort(superiors);
  NumberNode virtualSuperior;
  if (stray != NULL) {
    virtualSuperior.inferiors.push_back(stray);
    mainChain.push_back(&virtualSuperior);
  }

  NumberNodeVec sortedSuperiors = mainChain;
  if (!mainChain.empty())
    mainChain.insert(mainChain.begin(), sortedSuperiors[0]->inferiors.back());

  std::size_t pendCount = sortedSuperiors.size();

  if (pendCount > 1) {
    std::size_t previous = 1;
    std::size_t jacobIndex = 3;

    while (previous < pendCount) {
      std::size_t current = jacobsthal(jacobIndex);

      if (current > pendCount)
        current = pendCount;

      for (std::size_t i = previous; i < current; ++i)
        sortedSuperiors[i]->chainPosition = i + previous;

      std::size_t pendIndex = current;

      while (pendIndex > previous) {
        --pendIndex;
        NumberNode *superior = sortedSuperiors[pendIndex];
        std::size_t insertPos = binaryInsert(mainChain, superior->inferiors.back(),
                                             superior->chainPosition);

        for (std::size_t i = previous; i < pendIndex; ++i) {
          if (sortedSuperiors[i]->chainPosition >= insertPos)
            sortedSuperiors[i]->chainPosition += 1;
        }
      }

      previous = current;
      ++jacobIndex;
    }
  }

  if (stray != NULL)
    mainChain.pop_back();

  for (std::size_t i = 0; i < superiors.size(); ++i)
    superiors[i]->inferiors.pop_back();

  return mainChain;
}
} // namespace VectorSort

namespace DequeSort {
struct NumberNode;
typedef std::deque<NumberNode *> NumberNodeDeque;
struct NumberNode {
  int number;
  NumberNodeDeque inferiors;
  std::size_t chainPosition;
  NumberNode(int n = 0) : number(n), chainPosition(0) {}
};

static std::size_t binaryInsert(NumberNodeDeque &chain, NumberNode *element,
                                std::size_t upperBound) {
  std::size_t insertPosition = 0;

  while (insertPosition < upperBound) {
    std::size_t middle = insertPosition + (upperBound - insertPosition) / 2;

    if (chain[middle]->number < element->number)
      insertPosition = middle + 1;
    else
      upperBound = middle;
  }
  chain.insert(chain.begin() + insertPosition, element);
  return insertPosition;
}

static NumberNodeDeque mergeInsertionSort(const NumberNodeDeque &numbers) {
  if (numbers.size() <= 1)
    return numbers;

  NumberNodeDeque superiors;
  NumberNode *stray = NULL;

  if (numbers.size() % 2 != 0)
    stray = numbers.back();

  for (std::size_t i = 0; i + 1 < numbers.size(); i += 2) {
    NumberNode *superior;
    NumberNode *inferior;

    if (numbers[i]->number < numbers[i + 1]->number) {
      superior = numbers[i + 1];
      inferior = numbers[i];
    } else {
      superior = numbers[i];
      inferior = numbers[i + 1];
    }
    superior->inferiors.push_back(inferior);
    superiors.push_back(superior);
  }

  NumberNodeDeque mainChain = mergeInsertionSort(superiors);
  NumberNode virtualSuperior;
  if (stray != NULL) {
    virtualSuperior.inferiors.push_back(stray);
    mainChain.push_back(&virtualSuperior);
  }

  NumberNodeDeque sortedSuperiors = mainChain;
  if (!mainChain.empty())
    mainChain.insert(mainChain.begin(), sortedSuperiors[0]->inferiors.back());

  std::size_t pendCount = sortedSuperiors.size();

  if (pendCount > 1) {
    std::size_t previous = 1;
    std::size_t jacobIndex = 3;

    while (previous < pendCount) {
      std::size_t current = jacobsthal(jacobIndex);

      if (current > pendCount)
        current = pendCount;

      for (std::size_t i = previous; i < current; ++i)
        sortedSuperiors[i]->chainPosition = i + previous;

      std::size_t pendIndex = current;

      while (pendIndex > previous) {
        --pendIndex;
        NumberNode *superior = sortedSuperiors[pendIndex];
        std::size_t insertPos = binaryInsert(mainChain, superior->inferiors.back(),
                                             superior->chainPosition);

        for (std::size_t i = previous; i < pendIndex; ++i) {
          if (sortedSuperiors[i]->chainPosition >= insertPos)
            sortedSuperiors[i]->chainPosition += 1;
        }
      }

      previous = current;
      ++jacobIndex;
    }
  }

  if (stray != NULL)
    mainChain.pop_back();

  for (std::size_t i = 0; i < superiors.size(); ++i)
    superiors[i]->inferiors.pop_back();

  return mainChain;
}
} // namespace DequeSort

void PmergeMe::sort(std::vector<int> &container) {
  if (container.size() <= 1)
    return;

  std::vector<VectorSort::NumberNode> pool(container.size());
  VectorSort::NumberNodeVec numbers(container.size());

  for (std::size_t i = 0; i < container.size(); ++i) {
    pool[i].number = container[i];
    numbers[i] = &pool[i];
  }

  VectorSort::NumberNodeVec sorted = VectorSort::mergeInsertionSort(numbers);

  for (std::size_t i = 0; i < sorted.size(); ++i)
    container[i] = sorted[i]->number;
}

void PmergeMe::sort(std::deque<int> &container) {
  if (container.size() <= 1)
    return;

  std::deque<DequeSort::NumberNode> pool(container.size());
  DequeSort::NumberNodeDeque numbers(container.size());

  for (std::size_t i = 0; i < container.size(); ++i) {
    pool[i].number = container[i];
    numbers[i] = &pool[i];
  }

  DequeSort::NumberNodeDeque sorted = DequeSort::mergeInsertionSort(numbers);

  for (std::size_t i = 0; i < sorted.size(); ++i)
    container[i] = sorted[i]->number;
}
