// CODE

import { z } from "zod";

const StarWarsPerson = z.object({
  name: z.string(),
});

const StarWarsPeopleResults = z.object({
  results: z.array(StarWarsPerson),
});

type StarWarsPeopleInterface = z.infer<typeof StarWarsPeopleResults>

const logStarWarsPeopleResults = (data: StarWarsPeopleInterface) => {
  //                                    ^ 🕵️‍♂️
  data.results.map((person) => {
    console.log(person.name);
  });
};
