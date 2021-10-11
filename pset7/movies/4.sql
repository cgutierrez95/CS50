select count(a.title)
    from movies a
    left join ratings b on a.id = b.movie_id
    where b.rating = 10;