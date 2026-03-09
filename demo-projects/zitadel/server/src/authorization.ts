import { createMongoAbility, AbilityBuilder, type MongoAbility, type MongoQuery } from '@casl/ability';

class Article {
    id: number = 0
    title: string = ""
    content: string = ""
    authorId: number = 0
    __caslSubjectType__ = 'Article'
    static __caslSubjectType__ = 'Article'
    constructor(data: {
        id?: number,
        title?: string,
        content?: string,
        authorId?: number
    } = {}) {
        this.id = data.id ?? this.id;
        this.title = data.title ?? this.title;
        this.content = data.content ?? this.content;
        this.authorId = data.authorId ?? this.authorId;
    }
}

type CRUD = 'create' | 'read' | 'update' | 'delete';
type Abilities = ['read', 'User'] | [CRUD, 'Article'] | ['view' | 'update', 'Site'];

const { can, cannot, build, rules } = new AbilityBuilder(createMongoAbility)

// Option 1: Define rules with separate action and subject type
const allowedActions = [
    {
        action: "view:Site",
        subject: "Site",
        conditions: { id: "08df36fa0000000000000000", __caslSubjectType__: "Site" }
    },
    {
        action: "update:Site", 
        subject: "Site",
        conditions: { id: "08df36fa0000000000000000", __caslSubjectType__: "Site" }
    }
]

for (const rule of allowedActions) {
    can(rule.action,  rule.conditions);
}

const ability = build();

const site = {
    __caslSubjectType__: "Site",
    id: "08df36fa0000000000000000",
}

console.log(ability.can('view:Site', site)); // true
console.log(ability.can('update:Site', site)); // true

// Option 2: Alternative approach using specific subject instances
// const { can: can2, cannot: cannot2, build: build2 } = new AbilityBuilder(createMongoAbility)

// const allowedActions2 = [
//     {
//         action: "view",
//         subject: {
//             __caslSubjectType__: "Site",
//             id: "08df36fa0000000000000000",
//         },
//     }, {
//         action: "update",
//         subject: {
//             __caslSubjectType__: "Site",
//             id: "08df36fa0000000000000000",
//         },
//     }
// ]

// for (const rule of allowedActions2) {
//     can2(rule.action, rule.subject);
// }

// const ability2 = build2();

// console.log(ability2.can('view', site)); // true
// console.log(ability2.can('update', site)); // true