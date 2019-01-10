import { TestdDirective } from './testd.directive';
import tokenizerModule from '../binding.js';


describe('TestdDirective', () => {
  it('should create an instance', () => {
    const directive = new TestdDirective();
    expect(directive).toBeTruthy();
  });
});
