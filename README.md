# Dependencies: 
- [cjson](https://github.com/DaveGamble/cJSON)

# How to compile:
`your_favorite_c_compiler main.c date.c grade.c -lcjson -o calculator.bin`

# What does it do?
reads all your grades with their weight and tells you what score do you need to pass the subject.
It sorts the grades by date.

# How does it works?
`calculator.bin json_file`

# JSON Structure
```
{
    /* score needed to pass the subject */
    "minimum": int,

    /* array of all your grades */
    "grades": [
        {
            /* name of the grade */
            "name": "test 1",

            /* optional, date of the grade, format %d-%d */
            "date": "01-03",

            /* percentage of the score divided by 100 obtained that will be substracted to the minimum, example: 20% -> 0.20 */
            "weight": double,

            /* optional, score obtained of the grade */
            "score": double
        }
    ]
}
```
