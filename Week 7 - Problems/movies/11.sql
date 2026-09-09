-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT movies.title
FROM movies
    JOIN ratings on movies.id = ratings.movie_id
WHERE movies.id IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id IN
    (
        SELECT id
        FROM people
        WHERE name = 'Chadwick Boseman'
    )
)
ORDER BY ratings.rating DESC
LIMIT 5;
