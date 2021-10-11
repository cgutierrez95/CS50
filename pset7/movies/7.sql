select a.title, b.rating
    from movies a
    left join ratings b on a.id = b.movie_id
    where year = 2010
    order by b.rating desc, a.title;