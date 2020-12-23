# competivie-programming

Hi guys,

This project helps you to organize snippents in accecible ways.
The intended usage of the probject is mostly for Competitive Programming.

The code style for programming contests is deeply personal and I don't expect that it would be easy to reuse my snippets.
But I hope that you can take and adopt the main idea.
Which is enhasing your productivity during the programming contest by:
* Writing reusable tested snippets;
* Providing natural access to the snippets.

What can be more natural than just importing a function/class by standart means of the programming language?



Here are principles and ideas behind the project:
1. Write snippets only when you are practicing. The project is suppouse to enhance your speed, but not to slow you down. Designing reusable code takes time.
2. The main project should be correct at least from the compilier perspective. That is the way to make autocompletion work.
3. Write a snippet only if you need it to solve a problem. Write as little as you need. The solved problem means that your snippet is correct. That is the way to avoid untested code. The last thing you need during the contest is to debug a snippet that you wrote year ago.

Requirements:

Nice to have:

1. [python-codeforces](https://github.com/Mukundan314/python-codeforces) - provides ability to download examples by PROBLEM_ID.
2. [jngen](https://github.com/ifsmirnov/jngen) - super useful generators for stress testing.
3. [unifdef](http://dotat.at/prog/unifdef/) - nice tool to strip out #ifdef LOCAL from code.
