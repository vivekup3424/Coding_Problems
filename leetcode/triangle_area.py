def triangle_area(base: float, height: float) -> float:
    return 0.5 * base * height


if __name__ == "__main__":
    base = float(input("Enter base: "))
    height = float(input("Enter height: "))
    print(f"Area = {triangle_area(base, height)}")
