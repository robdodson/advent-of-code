import { readFileSync } from 'fs';

const input = readFileSync(new URL('./input.txt', import.meta.url), 'utf8');
const measurements = input.split('\n').map(Number);

function sum(collection, idx) {
  return collection[idx] + collection[idx + 1] + collection[idx + 2];
}

let total = 0;
for (let i = 0; i < measurements.length - 3; i++) {
  let window1 = sum(measurements, i);
  let window2 = sum(measurements, i + 1);

  if (window1 < window2) {
    total += 1;
  }
}

console.log(total);
