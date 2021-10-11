select a.title 
    from movies a
    left join ratings b on a.id = b.movie_id
    left join stars c on a.id = c.movie_id
    left join people d on c.person_id = d.id
    where d.name ="Chadwick Boseman"
    order by b.rating desc
    limit 5;