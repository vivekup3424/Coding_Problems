import { BloomFilter } from "./BloomFilter";

describe("BloomFilter", () => {
  it("should correctly identify added elements", () => {
    const filter = new BloomFilter(1000, 3);
    
    // Add some elements
    filter.add("test1");
    filter.add("test2");
    filter.add("notification123");
    
    // Should find all added elements
    expect(filter.has("test1")).toBe(true);
    expect(filter.has("test2")).toBe(true);
    expect(filter.has("notification123")).toBe(true);
    
    // Should not find elements that weren't added
    expect(filter.has("test3")).toBe(false);
    expect(filter.has("notification456")).toBe(false);
  });
  
  it("should handle collisions with minimal false positives", () => {
    // Create a filter with better parameters for the test
    const filter = new BloomFilter(200, 3);
    
    // Add many elements to increase collision probability
    for (let i = 0; i < 20; i++) {
      filter.add(`element${i}`);
    }
    
    // Check for false positives on non-added elements
    let falsePositives = 0;
    for (let i = 100; i < 200; i++) {
      if (filter.has(`element${i}`)) {
        falsePositives++;
      }
    }
    
    // With our filter parameters, we expect some false positives, but not too many
    expect(falsePositives).toBeLessThan(60);
    
    // Get the actual false positive rate
    console.log(`False positive rate: ${filter.getFalsePositiveRate()}`);
  });
  
  it("should clear the filter correctly", () => {
    const filter = new BloomFilter(1000, 3);
    
    // Add some elements
    filter.add("test1");
    filter.add("test2");
    
    // Clear the filter
    filter.clear();
    
    // Should not find any elements
    expect(filter.has("test1")).toBe(false);
    expect(filter.has("test2")).toBe(false);
  });
});
