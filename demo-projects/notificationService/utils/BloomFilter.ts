export class BloomFilter {
  private bitArray: boolean[];
  private hashFunctions: ((key: string) => number)[];
  private size: number;

  constructor(size: number = 10000, numHashFunctions: number = 3) {
    this.size = size;
    this.bitArray = new Array(size).fill(false);
    this.hashFunctions = this.createHashFunctions(numHashFunctions);
  }

  private createHashFunctions(count: number): ((key: string) => number)[] {
    const primes = [17, 31, 61, 127, 257, 509, 1021, 2053, 4099, 8191];
    const functions: ((key: string) => number)[] = [];
    
    for (let i = 0; i < count; i++) {
      const prime = primes[i % primes.length];
      functions.push((key: string) => {
        let hash = 0;
        // Jenkins One-at-a-time hash
        for (let j = 0; j < key.length; j++) {
          hash += key.charCodeAt(j);
          hash += (hash << 10);
          hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        
        // Apply prime multiplier for this hash function
        return Math.abs((hash * prime) % this.size);
      });
    }
    
    return functions;
  }

  /**
   * Add a key to the bloom filter
   */
  add(key: string): void {
    for (const hashFunc of this.hashFunctions) {
      const index = hashFunc(key);
      this.bitArray[index] = true;
    }
  }

  /**
   * Check if a key might exist in the bloom filter
   * False positives are possible, but false negatives are not
   */
  has(key: string): boolean {
    for (const hashFunc of this.hashFunctions) {
      const index = hashFunc(key);
      if (!this.bitArray[index]) {
        return false; // Definitely not in the set
      }
    }
    return true; // Might be in the set
  }
  
  /**
   * Get estimated false positive rate based on current fill
   */
  getFalsePositiveRate(): number {
    // Count filled bits
    const filledBits = this.bitArray.filter(bit => bit).length;
    // Calculate fill ratio
    const fillRatio = filledBits / this.size;
    // Calculate false positive probability using standard bloom filter formula
    return Math.pow(1 - Math.exp(-this.hashFunctions.length * filledBits / this.size), this.hashFunctions.length);
  }
  
  /**
   * Reset the bloom filter
   */
  clear(): void {
    this.bitArray.fill(false);
  }
}
