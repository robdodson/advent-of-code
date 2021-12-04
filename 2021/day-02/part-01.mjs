import { readFileSync } from 'fs';

const input = readFileSync(new URL('./input.txt', import.meta.url), 'utf8');
const steps = input.split('\n').map((line) => {
  const tuple = line.split(' ');
  return [tuple[0], Number(tuple[1])];
});

// const steps = [
//   ['forward', 5],
//   ['down', 5],
//   ['forward', 8],
//   ['up', 3],
//   ['down', 8],
//   ['forward', 2],
// ];

let horizontal = 0;
let depth = 0;
for (const step of steps) {
  const direction = step[0];
  const magnitude = step[1];

  switch (direction) {
    case 'forward':
      horizontal += magnitude;
      break;

    case 'down':
      depth += magnitude;
      break;

    case 'up':
      depth -= magnitude;
      break;

    default:
      break;
  }
}

console.log(horizontal * depth);
