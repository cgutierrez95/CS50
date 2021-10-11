select a.title 
    from (select c.title, b.movie_id, count(1) as cuenta
        from people a
        left join stars b on a.id = b.person_id
        left join movies c on b.movie_id = c.id
        where a.name = "Helena Bonham Carter" or a.name = "Johnny Depp"
        group by b.movie_id
        having cuenta > 1
        order by cuenta) a;