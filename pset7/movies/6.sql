select avg(b.rating)
    from movies a
    left join ratings b on a.id = b.movie_id 
    where a.year = 2012;