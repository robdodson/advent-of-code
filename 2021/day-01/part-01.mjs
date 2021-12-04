import { readFileSync } from 'fs';

const input = readFileSync('./input.txt', 'utf8');
const measurements = input.split('\n').map(Number);

let total = 0;
for (let i = 1; i < measurements.length; i++) {
  if (measurements[i] > measurements[i - 1]) {
    total += 1;
  }
}

console.log(total);
