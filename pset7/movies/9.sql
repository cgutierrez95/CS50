select c.name
    from movies a
    left join stars b on a.id = b.movie_id
    left join people c on b.person_id = c.id
    where a.year = 2004
    group by c.name
    order by c.birth;