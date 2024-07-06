CREATE TABLE ingredients(
    id INTEGER PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    title VARCHAR(255) UNIQUE NOT NULL 
);

ALTER TABLE ingredients
ADD COLUMN image VARCHAR(255) NOT NULL;

ALTER TABLE ingredients
ADD COLUMN type VARCHAR(255) NOT NULL;

INSERT INTO ingredients (
  title, image, type
) VALUES
  ( 'avocado', 'avocado.jpg', 'fruit' ),
  ( 'banana', 'banana.jpg', 'fruit' ),
  ( 'beef', 'beef.jpg', 'meat' ),
  ( 'black_pepper', 'black_pepper.jpg', 'other' ),
  ( 'blueberry', 'blueberry.jpg', 'fruit' ),
  ( 'broccoli', 'broccoli.jpg', 'vegetable' ),
  ( 'carrot', 'carrot.jpg', 'vegetable' ),
  ( 'cauliflower', 'cauliflower.jpg', 'vegetable' ),
  ( 'cherry', 'cherry.jpg', 'fruit' ),
  ( 'chicken', 'chicken.jpg', 'meat' ),
  ( 'corn', 'corn.jpg', 'vegetable' ),
  ( 'cucumber', 'cucumber.jpg', 'vegetable' ),
  ( 'eggplant', 'eggplant.jpg', 'vegetable' ),
  ( 'fish', 'fish.jpg', 'meat' ),
  ( 'flour', 'flour.jpg', 'other' ),
  ( 'ginger', 'ginger.jpg', 'other' ),
  ( 'green_bean', 'green_bean.jpg', 'vegetable' ),
  ( 'onion', 'onion.jpg', 'vegetable' ),
  ( 'orange', 'orange.jpg', 'fruit' ),
  ( 'pineapple', 'pineapple.jpg', 'fruit' ),
  ( 'potato', 'potato.jpg', 'vegetable' ),
  ( 'pumpkin', 'pumpkin.jpg', 'vegetable' ),
  ( 'raspberry', 'raspberry.jpg', 'fruit' ),
  ( 'red_pepper', 'red_pepper.jpg', 'vegetable' ),
  ( 'salt', 'salt.jpg', 'other' ),
  ( 'spinach', 'spinach.jpg', 'vegetable' ),
  ( 'strawberry', 'strawberry.jpg', 'fruit' ),
  ( 'sugar', 'sugar.jpg', 'other' ),
  ( 'tomato', 'tomato.jpg', 'vegetable' ),
  ( 'watermelon', 'watermelon.jpg', 'fruit' )
ON CONFLICT DO NOTHING;

UPDATE ingredients
SET image = 'watermelon.jpg'
WHERE title = 'watermelon';

SELECT id, title, image
FROM ingredients
LIMIT 5;

SELECT id, title, image
FROM ingredients
LIMIT 5
OFFSET 5;

SELECT *
FROM ingredients
WHERE type = 'fruit';

SELECT *
FROM ingredients
WHERE id <= 10
  OR id >= 20;
