SELECT DISTINCT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE movies.id IN (
    SELECT movie_id FROM stars WHERE person_id = (
        SELECT id FROM people WHERE name = 'Bradley Cooper'
    )
    INTERSECT SELECT movie_id FROM stars WHERE person_id = (
        SELECT id FROM people WHERE name = 'Jennifer Lawrence'
    )
);
