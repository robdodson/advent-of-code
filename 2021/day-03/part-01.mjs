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

let gamma = '';
let epsilon = '';

let position = 0;
let positions = lines[0].length;
while (position < positions) {
  let line = 0;
  let alpha = 0;
  let beta = 0;
  while (line < lines.length) {
    if (lines[line][position] === '0') {
      alpha += 1;
    } else {
      beta += 1;
    }

    line += 1;
  }
  if (alpha > beta) {
    gamma = gamma + '0';
    epsilon = epsilon + '1';
  } else {
    gamma = gamma + '1';
    epsilon = epsilon + '0';
  }
  position += 1;
}

gamma = parseInt(gamma, 2);
epsilon = parseInt(epsilon, 2);
console.log(gamma * epsilon);
