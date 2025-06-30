import { defineAbility } from "@casl/ability";
interface User {
    isLoggedIn?: boolean,
    id: number
}
interface Article {
    content: string,
    authorId ?: number,
}
const generateUserAbility = (user: User) => defineAbility((can) => {
    can('read', Article);

    if (user.isLoggedIn) {
        can('update', 'Article', { authodId: user.id });
        can('create', 'Comment');
        can('update', 'Comment', { authodId: user.id });
    }
})
const user: User = { id: 1 }
const userAbility = generateUserAbility(user);
const article1 : Article = {
    content : "Something Something",
    authorId: 1,
}
const article12: Article = {
    content: "Whatever, man",
    authorId: 12,
}