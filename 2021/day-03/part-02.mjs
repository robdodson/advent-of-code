import { readFileSync } from 'fs';

const input = readFileSync(new URL('./input.txt', import.meta.url), 'utf8');
const lines = input.split('\n');
// prettier-ignore
// const lines = [
//   '00100',
//   '11110',
//   '10110',
//   '10111',
//   '10101',
//   '01111',
//   '00111',
//   '11100',
//   '10000',
//   '11001',
//   '00010',
//   '01010',
// ];

/**
 * Takes a list of strings representing binary numbers and divide them into
 * arrays based on which digit is at the specified position. Strings with 0 at
 * the position go into the zeroLines array, and strings with a 1 go into the
 * oneLines array.
 * Count up how many lines have a 0 at the position, and how many have a 1
 * at the position.
 * If the preference is 'greater', return the group with the greater number of lines.
 * If the preference is 'lesser', return the group with the lesser number of lines.
 * If there is a tie, return the group that matches the preference (zeroLines for 'lesser' and oneLines for 'greater').
 * @param {string[]} list
 * @param {number} position
 * @param {'greater'|'lesser'} preference
 * @returns {string[]}
 */
function findMostCommonValue(list, position, preference) {
  let line = 0;
  let linesWithZero = 0; // count of lines that start with 0
  let linesWithOne = 0; // count of lines that start with 1
  let zeroLines = []; // collection of lines that start with 0
  let oneLines = []; // collection of lines that start with 1
  while (line < list.length) {
    if (list[line][position] === '0') {
      linesWithZero += 1;
      zeroLines.push(list[line]);
    } else {
      linesWithOne += 1;
      oneLines.push(list[line]);
    }
    line += 1;
  }

  if (linesWithZero === linesWithOne) {
    if (preference === 'lesser') {
      return zeroLines;
    } else {
      return oneLines;
    }
  }

  if (linesWithZero > linesWithOne) {
    if (preference === 'lesser') {
      return oneLines;
    } else {
      return zeroLines;
    }
  } else if (linesWithZero < linesWithOne) {
    if (preference === 'lesser') {
      return zeroLines;
    } else {
      return oneLines;
    }
  }
}

/**
 * @param {'oxygen' | 'co2'} type
 * @returns {string}
 */
function findRating(type) {
  const preference = type === 'oxygen' ? 'greater' : 'lesser';
  let collection = [...lines];
  let idx = 0;
  while (collection.length > 1) {
    collection = findMostCommonValue(collection, idx, preference);
    idx += 1;
  }
  return collection[0];
}

const oxygen = findRating('oxygen');
const co2 = findRating('co2');

console.log(parseInt(oxygen, 2) * parseInt(co2, 2));
